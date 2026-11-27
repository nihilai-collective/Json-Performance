
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2942.28 | 0.694538 | 5488.29ms | 699405 | 30 | 7.43709e+07 | 226697 | 0.51837 | 1(Win) | true |
| Glaze | 2465.36 | 0.202105 | 7111.49ms | 699405 | 80 | 2.39189e+07 | 270550 | 0.0650949 | 2(Loss) | true |
| simdjson (ondemand) | 1644.96 | 0.115135 | 5692.52ms | 767297 | 160 | 4.19715e+07 | 444845 | 0.286915 | 3(Loss) | true |
