
----
### Prettify Test Write Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3398.26 | 0.132298 | 5647.83ms | 699405 | 160 | 1.07888e+07 | 196278 | 0.425502 | 1(Win) | true |
| Glaze | 2308.49 | 0.319568 | 8301.87ms | 699405 | 160 | 1.3641e+08 | 288935 | 0.307819 | 2(Loss) | true |
| simdjson (ondemand) | 1413.3 | 0.435305 | 6872.86ms | 767297 | 640 | 3.25107e+09 | 517761 | 0.788168 | 3(Loss) | true |
