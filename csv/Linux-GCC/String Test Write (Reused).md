
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5710.82 | 0.0335163 | 80.3098ms | 4215 | 640 | 35.6197 | 703.881 | 0.0603431 | 0.417587 | 1(Win) | true |
| simdjson (reflection) | 3960.85 | 0.110164 | 105.946ms | 4215 | 30 | 37.4989 | 1014.87 | 0.0558678 | 0.608992 | 2(Loss) | true |
| Glaze | 2686.09 | 0.0535009 | 151.745ms | 4215 | 40 | 25.641 | 1496.5 | 0.0133663 | 0.906115 | 3(Loss) | true |
