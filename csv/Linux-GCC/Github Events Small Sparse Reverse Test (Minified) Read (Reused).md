
----
### Github Events Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3682.38 | 0.0899112 | 765.219ms | 1691 | 1280 | 198.458 | 437.941 | 0.202954 | 1.52446 | 6.17386 | 1.09344 | 0.000867183 | 5.54406e-05 | 1.94042e-05 | 1(Win) | true |
| simdjson (ondemand) | 2678.43 | 0.106221 | 777.41ms | 1691 | 160 | 65.444 | 602.094 | 0.0405001 | 2.04801 | 8.15376 | 1.37433 | 0.00109403 | 7.39208e-06 | 0 | 2(Loss) | true |
