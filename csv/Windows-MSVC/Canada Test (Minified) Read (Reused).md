
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 196.567 | 1.16988 | 7758.58ms | 2090234 | 40 | 5.62997e+11 | 1.01411e+07 | 0.911191 | 12.595 | 1(Win) | true |
| simdjson (ondemand) | 185.025 | 1.12779 | 8124.49ms | 2090234 | 40 | 5.90536e+11 | 1.07737e+07 | 1.54835 | 13.3806 | 2(Loss) | true |
