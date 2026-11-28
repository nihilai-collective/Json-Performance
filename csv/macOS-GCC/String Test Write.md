
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 825.611 | 0.89854 | 499.725ms | 4215 | 160 | 306224 | 4868.8 | 0.429043 | 1(Win) | true |
| simdjson (reflection) | 763.048 | 0.313517 | 543.53ms | 4215 | 1280 | 349159 | 5268 | 0.958222 | 2(Loss) | true |
| Glaze | 502.735 | 0.251463 | 836.826ms | 4215 | 30 | 12127.9 | 7995.73 | 0.752688 | 3(Loss) | true |
