
----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9520.83 | 0.246342 | 762.214ms | 2963 | 4890 | 2613.97 | 296.795 | 0.0049273 | 0.605388 | 1.42457 | 0.193385 | 0.000338393 | 2.88493e-05 | 5.93551e-06 | 1(Win) | true |
| Glaze | 4242.73 | 0.230995 | 798.862ms | 2963 | 4890 | 11574 | 666.019 | 0.406373 | 1.26466 | 2.73068 | 0.379346 | 0.000339911 | 3.69934e-05 | 6.97077e-06 | 2(Loss) | true |
