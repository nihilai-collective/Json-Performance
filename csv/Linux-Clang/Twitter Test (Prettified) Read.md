
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16973.7 | 0.0660779 | 4297.37ms | 631514 | 320 | 175905 | 35481.9 | 0.126067 | 0.300002 | 1.69236 | 0.0983938 | 1.62853e-05 | 7.2247e-07 | 4.05771e-07 | 1(Win) | true |
| simdjson (stage-1) | 15249 | 0.0296046 | 4681.02ms | 631514 | 1280 | 174989 | 39494.9 | 0.134417 | 0.336216 | 1.59421 | 0.0666637 | 2.087e-05 | 1.37443e-06 | 1.06639e-06 | 2(Loss) | true |
