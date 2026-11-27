
----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 993.535 | 0.0727908 | 9460.84ms | 183677 | 1280 | 2.10817e+07 | 176308 | 0.326331 | 5.12926 | 23.4143 | 4.51526 | 0.00629566 | 1.75155e-05 | 8.5876e-06 | 1(Win) | true |
| simdjson (ondemand) | 414.423 | 0.0631257 | 5492.36ms | 183677 | 640 | 4.55632e+07 | 422679 | 0.165325 | 12.3009 | 58.2078 | 10.4338 | 0.0412745 | 2.39721e-05 | 1.67413e-05 | 2(Loss) | true |
