
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3537.59 | 0.179015 | 1016.64ms | 9378 | 640 | 13108.9 | 2528.15 | 0.0348696 | 1.44755 | 6.88718 | 1.07368 | 0.00142021 | 1.9827e-05 | 1.99936e-06 | 1(Win) | true |
| Jsonifier | 2825.01 | 0.0872231 | 1085.02ms | 9378 | 4890 | 37286.5 | 3165.85 | 0.300386 | 1.80842 | 7.64342 | 1.59565 | 0.00302259 | 3.44757e-05 | 9.59475e-06 | 2(Loss) | true |
| Glaze | 2646.01 | 0.0696556 | 1097.75ms | 9378 | 4890 | 27105.5 | 3380.02 | 0.0820918 | 1.93142 | 9.00812 | 1.74579 | 0.00298961 | 3.32327e-05 | 8.0247e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2317.69 | 0.227488 | 1147.33ms | 9378 | 320 | 24659 | 3858.83 | 0.040589 | 2.20528 | 9.61356 | 1.48688 | 0.00140922 | 3.36559e-05 | 1.26626e-05 | 4(Loss) | true |
