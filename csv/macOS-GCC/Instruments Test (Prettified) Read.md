
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2489.29 | 0.0642829 | 7355.74ms | 183677 | 2560 | 5.23829e+06 | 70368.7 | 0.14958 | 1(Win) | true |
| Jsonifier (two-stage) | 2417.94 | 0.076135 | 7471.33ms | 183677 | 4890 | 1.48763e+07 | 72445.1 | 0.677791 | 2(Loss) | true |
| Glaze | 2103.53 | 0.0580255 | 8466.34ms | 183677 | 2560 | 5.97712e+06 | 83273.5 | 0.110238 | 3(Loss) | true |
| simdjson (reflection) | 2088.68 | 0.0966395 | 8905.97ms | 183677 | 30 | 197060 | 83865.6 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1781.5 | 0.252587 | 9533.89ms | 183677 | 80 | 4.9346e+06 | 98326.4 | 0.0553566 | 5(Loss) | true |
