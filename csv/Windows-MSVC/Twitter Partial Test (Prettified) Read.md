
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7946.97 | 0.0518247 | 7655.15ms | 631514 | 1280 | 1.97445e+06 | 75784.7 | 0.121172 | 0.382332 | 1(Win) | true |
| Jsonifier (two-stage) | 7908.55 | 0.186609 | 7667.58ms | 631514 | 4890 | 9.87522e+07 | 76152.9 | 0.316597 | 0.384179 | 2(Loss) | true |
| simdjson (ondemand) | 5195.44 | 0.0979831 | 5959.04ms | 631514 | 160 | 2.06416e+06 | 115921 | 0.0231786 | 0.584862 | 3(Loss) | true |
| Glaze | 3597.74 | 0.219208 | 8685.57ms | 631514 | 2560 | 3.44714e+08 | 167399 | 1.10838 | 0.844673 | 4(Loss) | true |
