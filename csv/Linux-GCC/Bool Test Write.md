
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1954.86 | 0.0288956 | 47.0045ms | 905 | 640 | 10.4163 | 441.503 | 0.00778651 | 1.18874 | 1(Win) | true |
| simdjson (reflection) | 258.501 | 0.0501348 | 343.981ms | 905 | 40 | 112.076 | 3338.78 | 0.476685 | 9.5013 | 2(Loss) | true |
| Glaze | 196.394 | 0.0328546 | 453.174ms | 905 | 80 | 166.772 | 4394.61 | 0.0167791 | 12.5273 | 3(Loss) | true |
