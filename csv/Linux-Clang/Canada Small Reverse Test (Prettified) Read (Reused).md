
----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1909.81 | 0.0479472 | 1411.31ms | 11579 | 2560 | 19675.6 | 5782.04 | 0.0400326 | 2.66335 | 13.5323 | 2.2742 | 0.000666346 | 2.62463e-05 | 1.02556e-05 | 1(Win) | true |
| Jsonifier (generic) | 1871.44 | 0.0446296 | 1422.33ms | 11579 | 2560 | 17753.1 | 5900.58 | 0.0541033 | 2.71818 | 13.3974 | 2.43199 | 0.000979987 | 4.89504e-05 | 2.72247e-05 | 2(Loss) | true |
