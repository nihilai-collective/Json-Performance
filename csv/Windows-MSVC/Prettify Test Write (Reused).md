
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3565.87 | 0.290569 | 9562.07ms | 699405 | 40 | 1.18164e+07 | 187052 | 0.271156 | 0.852209 | 1(Win) | true |
| Glaze | 2888.91 | 0.07224 | 5889.77ms | 699405 | 640 | 1.78043e+07 | 230884 | 0.0931687 | 1.05196 | 2(Loss) | true |
| simdjson (ondemand) | 1460.89 | 0.324822 | 6362.42ms | 767297 | 40 | 1.05888e+08 | 500895 | 0.191691 | 2.07953 | 3(Loss) | true |
