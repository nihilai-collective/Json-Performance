
----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1300.31 | 0.0505941 | 6100.54ms | 65103 | 1280 | 746998 | 47747.9 | 0.00343753 | 3.90957 | 14.7429 | 2.84803 | 0.011774 | 1.98004e-05 | 1.02602e-05 | 1(Win) | true |
| simdjson (ondemand) | 647.007 | 0.104626 | 5575.6ms | 65103 | 320 | 3.2256e+06 | 95960.4 | 0.0100703 | 7.84683 | 28.3947 | 5.65665 | 0.0497105 | 3.12486e-05 | 1.91043e-05 | 2(Loss) | true |
