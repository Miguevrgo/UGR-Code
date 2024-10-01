use actix_files::{Files, NamedFile};
use actix_multipart::Multipart;
use actix_web::{get, post, App, HttpResponse, HttpServer, Result};
use futures_util::stream::StreamExt as _;
use lettre::message::header::ContentType;
use lettre::{Message, SmtpTransport, Transport};
use std::fs::File;
use std::io::Write;

#[get("/")]
async fn index() -> Result<NamedFile> {
    Ok(NamedFile::open("./static/index.html")?)
}

#[post("/send")] // Manejar el envío de datos del formulario
async fn handle_form(mut payload: Multipart) -> Result<HttpResponse> {
    while let Some(item) = payload.next().await {
        let mut field = item?;
        let content_disposition = field.content_disposition().unwrap();
        let filename = content_disposition.get_filename().unwrap_or("file");

        let filepath = format!("./uploads/{}", filename);
        let mut f = File::create(filepath)?;

        while let Some(chunk) = field.next().await {
            let data = chunk?;
            f.write_all(&data)?;
        }
    }

    send_email(
        "destinatario@correo.com",
        "Asunto del correo",
        "Cuerpo del correo",
    )
    .unwrap();

    Ok(HttpResponse::Ok().body("Correo enviado correctamente"))
}

fn send_email(to: &str, subject: &str, body: &str) -> Result<(), Box<dyn std::error::Error>> {
    let email = Message::builder()
        .from("no-reply@ejemplo.com".parse()?)
        .to(to.parse()?)
        .subject(subject)
        .header(ContentType::TEXT_PLAIN)
        .body(body.to_string())?;

    let mailer = SmtpTransport::relay("smtp.tu-servidor.com")?
        .credentials(("usuario_smtp", "contraseña_smtp").into())
        .build();

    mailer.send(&email)?;
    Ok(())
}

#[tokio::main]
async fn main() -> std::io::Result<()> {
    std::fs::create_dir_all("./uploads")?;

    HttpServer::new(|| {
        App::new()
            .service(index)
            .service(handle_form)
            .service(Files::new("/static", "./static")) // Sirviendo archivos estáticos
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
