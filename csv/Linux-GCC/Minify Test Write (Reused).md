
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21222.4 | 0.181827 | 2124.36ms | 466906 | 1280 | 1.86292e+06 | 20981.4 | 0.00114684 | 0.116513 | 1(Win) | true |
| simdjson (ondemand) | 18312.8 | 0.192219 | 2454.05ms | 466906 | 640 | 1.39804e+06 | 24315 | 0.164662 | 0.135049 | 2(Loss) | true |
| Glaze | 2809.5 | 0.124716 | 8142.74ms | 466906 | 320 | 1.25024e+07 | 158489 | 0.162811 | 0.881069 | 3(Loss) | true |
