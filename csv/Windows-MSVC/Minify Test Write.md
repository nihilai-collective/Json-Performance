
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3766.37 | 0.481487 | 6324.03ms | 466906 | 320 | 1.03689e+08 | 118224 | 0.356523 | 0.657182 | 1(Win) | true |
| Glaze | 1918.19 | 0.222711 | 6185.71ms | 466906 | 160 | 4.27641e+07 | 232133 | 0.0266621 | 1.29054 | 2(Loss) | true |
| simdjson (ondemand) | 1564.56 | 0.0884055 | 7359.48ms | 466906 | 640 | 4.05148e+07 | 284602 | 0.502988 | 1.5817 | 3(Loss) | true |
