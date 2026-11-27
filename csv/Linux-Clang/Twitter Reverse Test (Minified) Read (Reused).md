
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 782.149 | 0.0628652 | 8863.93ms | 264040 | 640 | 2.62157e+07 | 321944 | 0.358037 | 6.54587 | 25.6219 | 4.75593 | 0.0187692 | 0.000224049 | 3.38194e-05 | 1(Win) | true |
| simdjson (ondemand) | 287.574 | 0.259894 | 5659.05ms | 264040 | 40 | 2.07154e+08 | 875628 | 0.00857648 | 17.5848 | 71.2519 | 12.3902 | 0.0856003 | 0.000170997 | 5.95554e-05 | 2(Loss) | true |
