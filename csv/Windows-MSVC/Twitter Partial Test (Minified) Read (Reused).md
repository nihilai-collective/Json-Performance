
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9014.91 | 0.202674 | 5253.89ms | 466906 | 30 | 300644 | 49393.3 | 0.135153 | 0.274475 | 1(Win) | true |
| Jsonifier (two-stage) | 8900.6 | 0.225065 | 5233.94ms | 466906 | 640 | 8.11362e+06 | 50027.7 | 0.0696975 | 0.278009 | 2(Loss) | true |
| simdjson (ondemand) | 3337.47 | 0.170109 | 6945.94ms | 466906 | 320 | 1.64826e+07 | 133417 | 0.170928 | 0.741644 | 3(Loss) | true |
| Glaze | 3095.5 | 0.318406 | 7575.83ms | 466906 | 80 | 1.67823e+07 | 143846 | 0.247048 | 0.799694 | 4(Loss) | true |
