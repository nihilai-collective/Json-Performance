
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4335.6 | 0.455897 | 5170.95ms | 466906 | 640 | 1.40306e+08 | 102702 | 1.534 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4283.08 | 2.13752 | 5461.15ms | 466906 | 30 | 1.48145e+08 | 103962 | 3.44746 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3958.52 | 0.199382 | 6436.49ms | 466906 | 640 | 3.21919e+07 | 112486 | 0.0149375 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3954.59 | 0.108924 | 5728.87ms | 466906 | 2560 | 3.85074e+07 | 112597 | 0.172771 | 3(Tie) | true |
| Glaze | 2238 | 0.576243 | 5277.55ms | 466906 | 160 | 2.10315e+08 | 198962 | 2.05252 | 5(Loss) | true |
