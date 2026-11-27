
----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 974.831 | 0.0748488 | 5784.83ms | 409725 | 320 | 2.88036e+07 | 400833 | 0.026279 | 5.23472 | 25.3384 | 5.11631 | 0.00894374 | 0.0096078 | 1.00525e-05 | 1(Win) | true |
| simdjson (ondemand) | 495.262 | 0.147744 | 5340.46ms | 409725 | 30 | 4.07621e+07 | 788964 | 0.0441903 | 10.3397 | 47.5217 | 8.5845 | 0.0312106 | 0.0184327 | 6.46775e-05 | 2(Loss) | true |
