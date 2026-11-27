
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10270.4 | 0.046788 | 819.025ms | 11812 | 4890 | 1287.8 | 1096.82 | 0.272795 | 0.522435 | 2.52565 | 0.175669 | 8.50579e-05 | 9.78174e-06 | 1.50621e-06 | 1(Win) | true |
| simdjson (stage-1) | 9731.73 | 0.150133 | 826.094ms | 11812 | 30 | 90.6023 | 1157.53 | 0.121093 | 0.54794 | 2.81519 | 0.117084 | 8.74817e-05 | 1.1288e-05 | 0 | 2(Loss) | true |
