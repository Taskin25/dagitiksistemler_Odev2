# dagitiksistemler_Odev2

# Dağıtık Sistemler Projesi: MPI ve OpenMP ile Paralel Veri İşleme

## Proje Hakkında
Bu projede, dağıtık sistem mimarisinde paralel veri işleme tekniklerini kullanarak veri işleme süreçlerini hızlandırmayı hedefledim.
**MPI (Message Passing Interface)** ve **OpenMP (Open Multi-Processing)** kullanarak düğümler arası iletişim sağladım ve her bir düğümdeki 
çok çekirdekli işlem gücünden faydalandım. Proje, Docker konteynerleri kullanılarak çoklu düğüm yapısına sahip olacak şekilde tasarlandı. 
Her bir düğüm, MPI ile birbirleriyle iletişim kurarken, OpenMP ile paralel işlem yapacak.

## Kullanılan Teknolojiler
- **Docker & Docker Compose**: Konteyner bazlı dağıtık sistemi yönetmek ve yapılandırmak için.
- **MPI**: Düğümler arasında iletişim kurmak için.
- **OpenMP**: Aynı düğümde çok çekirdekli paralel işlem yapmak için.
- **C Programlama Dili**: MPI ve OpenMP'yi kullanarak paralel işleme kodları yazdım.
- **GitHub & YouTube**: Kodları GitHub'da paylaşacağım, tanıtım videosu ise YouTube'da olacak.

## Proje Yapısı
### 1. `docker-compose.yml`
Bu dosya, 4 konteynerli bir MPI ağı oluşturur. Her bir konteynerin nasıl yapılandırılacağını ve diğer konteynerlerle nasıl iletişim kuracağını belirler.
Docker Compose ile tüm konteynerler birlikte çalışacak şekilde başlatılabilir.

### 2. `mpi_node/`
- **`Dockerfile`**: MPI node'larını oluşturmak için gerekli yapılandırmalar burada yer alır.
 Her bir konteyner için MPI ortamı hazırlanır ve gerekli bağımlılıklar yüklenir.
  
- **`ssh_config.sh`**: Düğümler arasındaki SSH bağlantısını ayarlamak için kullanılan bir script dosyasıdır.
- Bu dosya, Docker konteynerlerindeki düğümler arasındaki güvenli iletişimi sağlamak için SSH anahtarlarını yapılandırır. Bu sayede, düğümler
 birbirleriyle iletişim kurabilir ve paralel işlemler sorunsuz bir şekilde gerçekleşir.

### 3. `shared/`
- **`hostfile`**: MPI'nin hangi düğümlerin birbirleriyle iletişim kuracağını tanımladığı dosya. Bu dosya, her düğümün adreslerini içerir ve MPI'nin
  hangi düğümlerle iletişim kuracağını belirlemesini sağlar. Bu dosya, MPI programının her düğüme hangi makine üzerinden ulaşacağı bilgisini içerir.
- **`mpi_program.c`**: OpenMP ve MPI kullanarak paralel işlem yapan C kodu. Bu dosya, çok çekirdekli ve çok düğümlü paralel işlemeyi birleştiren ana
  programdır. Burada, MPI ile düğümler arası veri iletişimi sağlanırken, her bir düğümde OpenMP ile paralel işlem yapılır. Bu, dağıtık sistemin iş yükünü
  eşit bir şekilde dağıtarak, genel işlem süresini azaltır.
- **`run_distributed.sh`**: Bu bash scripti, tüm dağıtık sistemi başlatmak için kullanılır. `docker-compose.yml` ile belirtilen konteynerler başlatılır
   ve her bir düğümde MPI programı çalıştırılır. Bu script, MPI'nin çalışması için gerekli ortamı hazırlar ve tüm düğümleri başlatır. Ayrıca, dağıtık işlem sürecini
  başlatmak için komut dosyasını çalıştırır.

## Nasıl Çalışıyor?
1. **MPI İletişimi**: Her düğüm, diğer düğümlerle MPI protokolü üzerinden veri iletişimi yapabiliyor. Bu, dağıtık sistemin paralel veri işleme gücünü artırıyor.
 Her düğüm, bir diğer düğümün verisini alır ve işler, ardından sonuçları diğer düğümlere iletir.
2. **OpenMP Paralel İşlem**: Aynı düğümde, birden fazla çekirdek kullanılarak işlemler paralel şekilde yapılabiliyor. OpenMP, her bir çekirdek için ayrı iş parçacıkları
    oluşturur ve bu parçacıklar, işlemleri paralel olarak yürütür.
3. **Docker ile Çoklu Düğüm Yapısı**: Docker konteynerleri ile her düğüm izole ediliyor ve Docker Compose ile tüm yapı kolayca yönetilebiliyor. Bu sayede her düğüm bağımsız
    çalışarak, tüm sistemin iş yükünü paylaşır.

## Performans Karşılaştırması
MPI ve OpenMP’nin paralel işleme üzerindeki etkilerini karşılaştırarak, her iki teknolojinin verimliliğini analiz edeceğim. MPI ile düğümler arası iletişimin ve OpenMP ile çok çekirdekli işlemenin sistem üzerindeki etkilerini ölçerek hangi yaklaşımın daha verimli olduğunu göreceğiz.

- **MPI**: Düğümler arasında iletişim sağlıyor, ama bu iletişim biraz daha maliyetli olabilir. Her düğüm kendi işlemlerini yaparken, veri alışverişi yapılması gerektiğinde zaman kaybı olabilir.
- **OpenMP**: Aynı düğümdeki çekirdekler arası paralellik sağlıyor ve daha hızlı işlem yapabiliyor, ama bu yalnızca tek bir makineyle sınırlı. Bununla birlikte, daha düşük gecikme süresi ile işlem yapılabilir.

## Sonuçlar
Proje sonunda, MPI ve OpenMP kullanarak paralel işleme süreçlerini optimize etmeyi başardım. MPI, düğümler arası iletişimi sağlarken, OpenMP ile aynı düğümde çok çekirdekli işlem gücünden yararlanarak daha hızlı veri işleme sağladım. Her iki teknolojinin birleşimi, dağıtık sistemin işlem gücünü önemli ölçüde artırdı ve daha verimli bir işleme süreci elde edildi.

Docker Compose ile dağıtık yapının yönetimi de büyük kolaylık sağladı. Her bir düğümün bağımsız çalışması ve sistemin tüm bileşenlerinin Docker konteynerleri içinde izole bir şekilde yönetilmesi, geliştirme sürecini hızlandırdı. Genel olarak, dağıtık sistemin sağladığı performans artışı ve yapılan optimizasyonlar, hedeflenen verimliliği elde etmemi sağladı.
