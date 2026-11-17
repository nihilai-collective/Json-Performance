
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9369.41 | 0.0815427 | 7188.29ms | 631514 | 1280 | 3.51659e+06 | 64279.3 | 0.09196 | 0.537036 | 2.70393 | 0.303616 | 0.000608353 | 5.54595e-06 | 2.27628e-06 | 1(Win) | true |
| Jsonifier | 9343.17 | 0.0737514 | 7193.41ms | 631514 | 2560 | 5.78573e+06 | 64459.8 | 0.260395 | 0.537422 | 2.70451 | 0.303765 | 0.000600841 | 1.45094e-05 | 5.9678e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8279.04 | 0.0296934 | 8035.72ms | 631514 | 4890 | 2.28157e+06 | 72745 | 0.0548643 | 0.608704 | 2.90635 | 0.296634 | 0.000619398 | 8.14092e-06 | 3.18772e-06 | 3(Loss) | true |
| Glaze | 4064.43 | 0.0382024 | 7975.07ms | 631514 | 640 | 2.05083e+06 | 148178 | 0.0073249 | 1.24376 | 5.34889 | 0.944944 | 0.00122265 | 7.47707e-06 | 4.50802e-06 | 4(Loss) | true |
