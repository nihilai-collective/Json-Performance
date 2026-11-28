
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1946.99 | 0.113093 | 44.0564ms | 905 | 80 | 20.1062 | 443.288 | 0.0760778 | 1.20275 | 1(Win) | true |
| simdjson (reflection) | 269.551 | 0.0375062 | 321.432ms | 905 | 30 | 43.2655 | 3201.9 | 0.202372 | 9.11182 | 2(Loss) | true |
| Glaze | 208.559 | 0.024218 | 417.98ms | 905 | 80 | 80.3538 | 4138.27 | 0.0126848 | 11.7922 | 3(Loss) | true |
