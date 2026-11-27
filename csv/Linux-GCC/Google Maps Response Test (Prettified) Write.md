
----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 30902 | 0.0935315 | 99.3969ms | 31235 | 160 | 130.06 | 963.95 | 0.125627 | 0.0779554 | 1(Win) | true |
| Glaze | 5546.84 | 0.177093 | 568.957ms | 31235 | 2560 | 231545 | 5370.26 | 0.47147 | 0.444098 | 2(Loss) | true |
| simdjson (reflection) | 583.161 | 0.379087 | 5220.23ms | 31235 | 40 | 1.49984e+06 | 51080.2 | 0.0716707 | 4.24316 | 3(Loss) | true |
