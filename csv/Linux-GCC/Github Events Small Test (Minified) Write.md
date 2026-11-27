
----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8504.68 | 0.0904947 | 743.583ms | 1996 | 640 | 26.2562 | 223.822 | 0.257631 | 0.715476 | 1.59719 | 0.26002 | 0.000501002 | 1.95704e-05 | 1.56563e-06 | 1(Win) | true |
| simdjson (reflection) | 6707.9 | 0.106683 | 747.343ms | 1996 | 40 | 3.66603 | 283.775 | 0.13783 | 0.887149 | 1.94539 | 0.288076 | 0.000501002 | 2.50501e-05 | 0 | 2(Loss) | true |
| Glaze | 5278.06 | 0.29264 | 754.723ms | 1996 | 4890 | 5446.88 | 360.651 | 0.346417 | 1.07863 | 3.45541 | 0.568637 | 0.000501924 | 6.86444e-05 | 4.35431e-05 | 3(Loss) | true |
