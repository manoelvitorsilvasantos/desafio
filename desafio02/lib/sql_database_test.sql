
//DROP TABLE IF EXISTS caixa;

CREATE TABLE IF NOT EXISTS caixa(
	codigo INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
 	vendedor TEXT NOT NULL,
	descricao TEXT NOT NULL,
	total_venda REAL NOT NULL,
	dt_venda DATETIME
);


DROP TABLE IF EXISTS bancos;

CREATE TABLE IF NOT EXISTS bancos(
  codigo_banco INT NOT NULL,
  nome_banco TEXT NOT NULL
);

INSERT INTO bancos(codigo_banco, nome_banco) VALUES
(6622, 'NUBANK'),
(6602, 'PICPAY'),
(4532, 'BRADESCO'),
(3312, 'SANTADER'),
(6479, 'BANCO_DO_BRASIL'),
(1400, 'ITAU'),
(1015, 'CAIXA');


CREATE TABLE IF NOT EXISTS empresa(
  codigo INTEGER NOT NULL PRIMARY KEY,
  pix TEXT NOT NULL,
  qrcode TEXT NOT NULL,
  banco_codigo INT NOT NULL,
  FOREIGN KEY(banco_codigo) REFERENCES bancos(codigo_banco)
);