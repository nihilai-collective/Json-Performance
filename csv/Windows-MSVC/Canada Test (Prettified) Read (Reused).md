
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1657.81 | 0.563219 | 5680.98ms | 5373214 | 80 | 2.42462e+10 | 3.091e+06 | 1.16995 | 1.83321 | 1(Win) | true |
| Jsonifier (two-stage) | 1580.56 | 0.943027 | 5744.46ms | 5373214 | 80 | 7.47799e+10 | 3.24208e+06 | 1.84359 | 1.92277 | 2(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1051.18 | 0.993102 | 8068.58ms | 5373214 | 30 | 7.03117e+10 | 4.87483e+06 | 2.6059 | 2.89106 | -(Loss) | false |
| Glaze | 938.088 | 0.697588 | 9373.99ms | 5373214 | 40 | 5.80818e+10 | 5.46249e+06 | 0.42614 | 3.23983 | 4(Loss) | true |
