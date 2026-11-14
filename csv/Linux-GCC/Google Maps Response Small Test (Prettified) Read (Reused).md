
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3470.85 | 0.0818208 | 1011.97ms | 9378 | 4890 | 21736.3 | 2576.77 | 0.0640228 | 1.50083 | 6.88878 | 0.984432 | 0.00162862 | 2.32455e-05 | 5.32072e-06 | 1(Win) | true |
| Jsonifier | 3320.62 | 0.104876 | 1022.26ms | 9378 | 4890 | 39016 | 2693.34 | 0.0572984 | 1.56602 | 6.95628 | 1.3264 | 0.0026782 | 2.29838e-05 | 1.01181e-05 | 2(Loss) | true |
| simdjson (reflection) | 3173.3 | 0.142712 | 1024.66ms | 9378 | 40 | 647.112 | 2818.38 | 0.206514 | 1.64699 | 6.656 | 0.953935 | 0.00110898 | 2.66581e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 2438.77 | 0.0299879 | 1119.3ms | 9378 | 320 | 387.009 | 3667.24 | 0.0528606 | 2.13615 | 8.39646 | 1.37577 | 0.00130292 | 1.66613e-05 | 5.33163e-06 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 2435.64 | 0.144349 | 1119.64ms | 9378 | 640 | 17980.6 | 3671.96 | 0.0925942 | 2.1349 | 8.81926 | 1.66112 | 0.00393741 | 1.34957e-05 | 2.4992e-06 | 4(Tie) | true |
