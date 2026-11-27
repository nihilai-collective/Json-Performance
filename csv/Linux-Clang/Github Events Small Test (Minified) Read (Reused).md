
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1474.25 | 0.159105 | 842.046ms | 1691 | 80 | 242.329 | 1093.89 | 0.172848 | 3.62364 | 12.9426 | 2.44471 | 0.000901833 | 0.000118273 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1360.74 | 0.062427 | 845.362ms | 1691 | 2560 | 1401.27 | 1185.14 | 0.134692 | 3.91312 | 15.1467 | 2.50503 | 0.00139502 | 9.4249e-05 | 3.14163e-05 | 2(Loss) | true |
