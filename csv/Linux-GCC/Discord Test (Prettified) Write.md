
----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24646.7 | 0.0605674 | 371.821ms | 94370 | 30 | 146.74 | 3651.53 | 0.708796 | 0.09968 | 1(Win) | true |
| Glaze | 4974.41 | 0.0914874 | 1815.16ms | 94370 | 4890 | 1.33973e+06 | 18092.2 | 0.411227 | 0.496949 | 2(Loss) | true |
| simdjson (reflection) | 528.791 | 0.21113 | 8815.74ms | 94370 | 160 | 2.06594e+07 | 170196 | 0.0644759 | 4.68063 | 3(Loss) | true |
