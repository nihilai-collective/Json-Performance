
----
### Instruments Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 513.465 | 1.10279 | 948.967ms | 4669 | 640 | 5.85317e+06 | 8671.88 | 0.534069 | 5.89486 | 1(Win) | true |
| simdjson (ondemand) | 204.534 | 0.20283 | 2379.55ms | 4669 | 320 | 623925 | 21770 | 1.01502 | 14.8467 | 2(Loss) | true |
