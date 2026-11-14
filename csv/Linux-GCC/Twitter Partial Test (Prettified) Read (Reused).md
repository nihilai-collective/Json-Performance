
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8990.87 | 0.0461752 | 7504.39ms | 631514 | 1280 | 1.22459e+06 | 66985.6 | 0.0109818 | 0.566439 | 2.7061 | 0.279964 | 0.000639773 | 6.13357e-06 | 5.25523e-06 | 1(Win) | true |
| Jsonifier | 8979.29 | 0.0315459 | 7535.48ms | 631514 | 4890 | 2.18916e+06 | 67072 | 0.0910309 | 0.566746 | 2.70704 | 0.280165 | 0.000666018 | 7.00721e-06 | 6.15135e-06 | 2(Loss) | true |
| simdjson (reflection) | 8279.04 | 0.0445223 | 8058.98ms | 631514 | 2560 | 2.68535e+06 | 72745 | 0.100469 | 0.610698 | 2.9944 | 0.286683 | 0.000760376 | 8.27562e-06 | 6.47625e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8111.12 | 0.048122 | 8211.65ms | 631514 | 4890 | 6.24312e+06 | 74251 | 0.0320494 | 0.624145 | 3.00402 | 0.284383 | 0.00061825 | 1.0579e-05 | 8.40289e-06 | 4(Loss) | true |
| Glaze | 3873.02 | 0.0374821 | 8361.72ms | 631514 | 2560 | 8.6967e+06 | 155501 | 0.0330885 | 1.3095 | 5.83003 | 0.956731 | 0.0013767 | 9.15521e-06 | 7.90635e-06 | 5(Loss) | true |
