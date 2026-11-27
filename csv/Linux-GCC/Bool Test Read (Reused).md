
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2358.95 | 0.0543844 | 39.6602ms | 905 | 640 | 25.3388 | 365.872 | 0.129139 | 0.97318 | 1(Win) | true |
| Jsonifier | 2142.39 | 0.0627503 | 43.389ms | 905 | 320 | 20.4495 | 402.856 | 0.046521 | 1.07691 | 2(Loss) | true |
| simdjson (reflection) | 1162.78 | 0.0837974 | 75.5171ms | 905 | 80 | 30.9494 | 742.25 | 0.0471317 | 2.04862 | 3(Loss) | true |
| simdjson (ondemand) | 500.299 | 0.0309723 | 178.395ms | 905 | 160 | 45.6776 | 1725.12 | 0.0228297 | 4.86773 | 4(Loss) | true |
