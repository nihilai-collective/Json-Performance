
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8734.78 | 0.0679777 | 5228.52ms | 466906 | 4890 | 5.87215e+06 | 50977.4 | 0.0639553 | 0.283295 | 1(Win) | true |
| Jsonifier | 8682.38 | 0.194436 | 5347.78ms | 466906 | 2560 | 2.54552e+07 | 51285 | 0.540843 | 0.284988 | 2(Loss) | true |
| simdjson (ondemand) | 8255.15 | 0.355697 | 5744.67ms | 466906 | 30 | 1.10431e+06 | 53939.2 | 0.00908513 | 0.299771 | 3(Loss) | true |
| simdjson (reflection) | 7777.38 | 0.187874 | 5825.39ms | 466906 | 160 | 1.85117e+06 | 57252.7 | 0.179603 | 0.318189 | 4(Loss) | true |
| Glaze | 3298.27 | 0.046332 | 7023.27ms | 466906 | 1280 | 5.00794e+06 | 135003 | 0.0604939 | 0.750506 | 5(Loss) | true |
