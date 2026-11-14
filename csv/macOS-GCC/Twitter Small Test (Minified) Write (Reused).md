
----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11092.5 | 2.45397 | 26.722ms | 2963 | 4890 | 191097 | 254.744 | 4.06191 | 1(Win) | true |
| simdjson (reflection) | 9748.24 | 2.28223 | 32.4188ms | 2963 | 4890 | 214013 | 289.872 | 0.421994 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 3208.15 | 2.22617 | 88.6372ms | 2963 | 320 | 123033 | 880.8 | 6.8932 | -(Loss) | false |
