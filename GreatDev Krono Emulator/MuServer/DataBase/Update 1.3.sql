USE [MuOnline]
GO
/****** Object:  StoredProcedure [dbo].[SP_CHECK_ILLUSION_TEMPLE]    Script Date: 2018.01.18. 0:53:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO




--//************************************************************************
--// 郴   侩 : 券康荤盔 1老 涝厘 冉荐 眉农
--// 何   辑 : 辑滚评 
--// 父甸老 : 2007.06. 7
--// 父甸捞 : goni
--// 
--//************************************************************************

CREATE PROCEDURE	[dbo].[SP_CHECK_ILLUSION_TEMPLE]
	@AccountID		varchar(10),	-- 拌沥疙
	@CharacterName	varchar(10),	-- 纳腐疙
	@Server		smallint		-- 辑滚
As
Begin
	DECLARE	@iMaxEnterCheck	INT
	DECLARE	@iNowEnterCheck	INT

	SET		@iMaxEnterCheck	= 6		-- 老老 弥措 涝厘啊瓷 冉荐
	
	BEGIN TRANSACTION
	
	SET NOCOUNT ON	

	IF EXISTS ( SELECT AccountID FROM T_ENTER_CHECK_ILLUSION_TEMPLE  WITH (READUNCOMMITTED) 
				WHERE  AccountID = @AccountID AND ServerCode = @Server AND CharName = @CharacterName )
	BEGIN
		SELECT @iNowEnterCheck = TodayEnterCount 
		FROM T_ENTER_CHECK_ILLUSION_TEMPLE  WITH (READUNCOMMITTED) 
		WHERE  AccountID = @AccountID AND ServerCode = @Server AND CharName = @CharacterName

		IF (@iNowEnterCheck >= @iMaxEnterCheck)
		BEGIN
			SELECT 0 As EnterResult	-- 荤盔 涝厘 阂啊瓷
		END
		ELSE
		BEGIN
			SELECT 1 As EnterResult	-- 荤盔 涝厘 啊瓷
		END
		
	END
	ELSE
	BEGIN
		SELECT 1 As EnterResult		-- 荤盔 涝厘 啊瓷
	END

	IF(@@Error <> 0 )
		ROLLBACK TRANSACTION
	ELSE	
		COMMIT TRANSACTION

	SET NOCOUNT OFF	
End


GO
/****** Object:  StoredProcedure [dbo].[SP_ENTER_ILLUSION_TEMPLE]    Script Date: 2018.01.18. 0:53:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO




--//************************************************************************
--// 郴   侩 : 券康荤盔 1老 涝厘 冉荐 刘啊
--// 何   辑 : 辑滚评 
--// 父甸老 : 2007.06. 7
--// 父甸捞 : goni
--// 
--//************************************************************************

CREATE PROCEDURE	[dbo].[SP_ENTER_ILLUSION_TEMPLE]
	@AccountID		varchar(10),	-- 拌沥疙
	@CharacterName	varchar(10),	-- 纳腐疙
	@Server		smallint		-- 辑滚
As
Begin
	BEGIN TRANSACTION
	
	SET NOCOUNT ON	

	IF EXISTS ( SELECT AccountID FROM T_ENTER_CHECK_ILLUSION_TEMPLE  WITH (READUNCOMMITTED) 
				WHERE  AccountID = @AccountID AND ServerCode = @Server AND CharName = @CharacterName )
	BEGIN
		UPDATE T_ENTER_CHECK_ILLUSION_TEMPLE 
		SET TodayEnterCount = TodayEnterCount + 1, LastEnterDate = GetDate()
		WHERE  AccountID = @AccountID AND ServerCode = @Server AND CharName = @CharacterName
	END
	ELSE
	BEGIN
		INSERT INTO T_ENTER_CHECK_ILLUSION_TEMPLE ( AccountID, CharName, ServerCode, TodayEnterCount, LastEnterDate ) VALUES (
			@AccountID,
			@CharacterName,
			@Server,
			1,
			DEFAULT
		)
	END

	IF(@@Error <> 0 )
		ROLLBACK TRANSACTION
	ELSE	
		COMMIT TRANSACTION

	SET NOCOUNT OFF	
End


GO
/****** Object:  Table [dbo].[T_ENTER_CHECK_ILLUSION_TEMPLE]    Script Date: 2018.01.18. 0:53:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[T_ENTER_CHECK_ILLUSION_TEMPLE](
	[AccountID] [varchar](10) NOT NULL,
	[CharName] [varchar](10) NOT NULL,
	[ServerCode] [tinyint] NOT NULL,
	[TodayEnterCount] [tinyint] NOT NULL,
	[LastEnterDate] [smalldatetime] NOT NULL,
 CONSTRAINT [PK_T_ENTER_CHECK_ILLUSION_TEMPLE] PRIMARY KEY CLUSTERED 
(
	[AccountID] ASC,
	[CharName] ASC,
	[ServerCode] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
ALTER TABLE [dbo].[T_ENTER_CHECK_ILLUSION_TEMPLE] ADD  CONSTRAINT [DF_T_ENTER_CHECK_ILLUSION_TEMPLE_LastEnterDate]  DEFAULT (getdate()) FOR [LastEnterDate]
GO
