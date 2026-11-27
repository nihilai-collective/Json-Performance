
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 785.128 | 0.27219 | 1549.36ms | 11812 | 1280 | 1.95219e+06 | 14347.7 | 0.128883 | 3.86501 | 1(Win) | true |
| simdjson (ondemand) | 641.562 | 0.135229 | 1879.09ms | 11812 | 2560 | 1.44327e+06 | 17558.4 | 0.27372 | 4.73091 | 2(Loss) | true |
