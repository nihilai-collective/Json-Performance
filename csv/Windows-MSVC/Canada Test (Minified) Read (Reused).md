
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 458.086 | 0.488337 | 7428.51ms | 2090234 | 80 | 3.61266e+10 | 4.35159e+06 | 0.100294 | 6.6343 | 1(Win) | true |
| simdjson (ondemand) | 451.261 | 0.52202 | 7536.62ms | 2090234 | 30 | 1.59526e+10 | 4.41741e+06 | 0.509746 | 6.73488 | 2(Loss) | true |
