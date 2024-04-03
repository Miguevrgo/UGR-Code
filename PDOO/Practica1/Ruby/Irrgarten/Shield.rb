class Shield
    def initialize(protection,uses)
        @protection = protection
        @uses = uses
    end

    def protect
        if @uses > 0
            @uses -= 1
            return @protection
        else
            return 0
        end
    end
    
    def to_s
        return "S[#{@protection},#{@uses}]"
    end
end
