
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1432.47 | 0.0357506 | 1314.41ms | 8150 | 2560 | 9632.76 | 5425.9 | 0.0409014 | 3.6199 | 15.6845 | 3.11767 | 0.00612049 | 2.49233e-05 | 8.24387e-06 | 1(Win) | true |
| simdjson (ondemand) | 804.422 | 0.0610026 | 1736.22ms | 8150 | 160 | 5558.58 | 9662.14 | 0.0406706 | 6.43217 | 28.3353 | 5.01902 | 0.0161281 | 2.9908e-05 | 1.07362e-05 | 2(Loss) | true |
