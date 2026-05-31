# 💣 C ile Mayın Tarlası (Minesweeper)

Bu proje, C programlama dili kullanılarak konsol (terminal) tabanlı geliştirilmiş klasik bir **Mayın Tarlası** oyunudur. Dinamik matris yönetimi, rekürsif hücre açma (flood fill) algoritması ve adil oyun mekanikleri içerir.

---

## ✨ Özellikler

* **Adil İlk Hamle Garantisi:** İlk bastığınız hücrede ve o hücrenin komşularında asla mayın olamaz. İlk hamleden kaybetmek yok!
* **Otomatik Genişleme:** 0 mayınlı bir hücre açtığınızda, etrafındaki güvenli alanlar otomatik olarak rekürsif bir şekilde açılır.
* **Bayrak Ekleme/Kaldırma:** Şüphelendiğiniz hücreleri `F` (Flag) komutu ile işaretleyebilir, fikrinizi değiştirirseniz bayrağı kaldırabilirsiniz.
* **Girdi Kontrolleri:** Hatalı koordinat, yanlış karakter veya zaten açılmış hücreler için gelişmiş hata mesajları barındırır.

---

## 🛠️ Teknik Detaylar

* **Dil:** C (C99 standardı uyumlu)
* **Tahta Boyutu:** 8x8 (Değiştirilebilir `SIZE` makrosu ile)
* **Mayın Sayısı:** 10 (Değiştirilebilir `MINES` makrosu ile)
* **Algoritmalar:** Rekürsif Alan Açma (Flood Fill yaklaşımı), Rastgele Mayın Dağıtımı (`rand()`).

---

## 🎮 Nasıl Oynanır?

Oyun başladığında terminale hamlenizi belirtmek için komut formatını girmeniz gerekir:
`[İşlem] [Satır] [Sütun]`

* **Hücre Açmak İçin (`O` veya `o`):** `O 2 3` (2. satır, 3. sütundaki hücreyi açar)
* **Bayrak Koymak/Kaldırmak İçin (`F` veya `f`):** `F 4 1` (4. satır, 1. sütuna bayrak koyar)

### Oyun Kuralları
1. Tüm güvenli hücreleri (mayınsız alanları) açtığınızda oyunu **kazanırsınız**.
2. Mayınlı bir hücreyi açarsanız oyun **biter**.

---
