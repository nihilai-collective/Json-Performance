
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16338.1 | 0.124499 | 2863.86ms | 475954 | 1280 | 1.53132e+06 | 27782 | 0.0806928 | 1(Win) | true |
| simdjson (reflection) | 12108.5 | 0.141812 | 3868.52ms | 475954 | 640 | 1.80865e+06 | 37486.4 | 0.0085357 | 2(Loss) | true |
| Glaze | 3734.84 | 0.0555458 | 6293.61ms | 475954 | 2560 | 1.16662e+07 | 121533 | 0.163884 | 3(Loss) | true |
