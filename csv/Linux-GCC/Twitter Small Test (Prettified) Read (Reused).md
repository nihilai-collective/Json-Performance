
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3107.11 | 0.144418 | 124.72ms | 3808 | 30 | 85.4759 | 1168.8 | 0.263068 | 0.779473 | 1(Win) | true |
| Jsonifier (two-stage) | 2720.79 | 0.0615773 | 141.937ms | 3808 | 160 | 108.085 | 1334.76 | 0.121424 | 0.892224 | 2(Loss) | true |
| simdjson (reflection) | 2699.27 | 0.197702 | 142.106ms | 3808 | 30 | 212.248 | 1345.4 | 0.217553 | 0.898748 | 3(Loss) | true |
| Glaze | 2304.66 | 0.0587611 | 168.736ms | 3808 | 80 | 68.5884 | 1575.76 | 0.194729 | 1.05655 | 4(Loss) | true |
| simdjson (ondemand) | 1496.41 | 0.299452 | 249.74ms | 3808 | 2560 | 135204 | 2426.87 | 0.429165 | 1.63626 | 5(Loss) | true |
