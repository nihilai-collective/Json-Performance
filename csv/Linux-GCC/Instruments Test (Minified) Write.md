
----
### Instruments Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17282.8 | 0.0291124 | 602.271ms | 108313 | 40 | 121.102 | 5976.77 | 0.0439007 | 0.142604 | 1(Win) | true |
| simdjson (reflection) | 14118.5 | 0.0309104 | 743.736ms | 108313 | 40 | 204.574 | 7316.3 | 0.0355497 | 0.174692 | 2(Loss) | true |
| Glaze | 2322.73 | 0.284753 | 4536.04ms | 108313 | 80 | 1.28289e+06 | 44471.6 | 0.209498 | 1.06525 | 3(Loss) | true |
