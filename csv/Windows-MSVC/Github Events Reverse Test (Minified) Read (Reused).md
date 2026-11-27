
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.164 | 0.97007 | 6464.11ms | 53331 | 320 | 9.94189e+07 | 57458.8 | 1.58678 | 3.43174 | 1(Win) | true |
| simdjson (ondemand) | 416.789 | 0.274273 | 6688.27ms | 53331 | 640 | 7.16925e+07 | 122029 | 0.188635 | 7.29083 | 2(Loss) | true |
