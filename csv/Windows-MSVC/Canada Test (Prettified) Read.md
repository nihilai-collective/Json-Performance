
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1566.68 | 0.470793 | 10153.9ms | 5373214 | 80 | 1.89696e+10 | 3.2708e+06 | 0.227141 | 1.93976 | 1(Win) | true |
| Jsonifier | 1485.68 | 0.703407 | 5193.97ms | 5373214 | 40 | 2.35446e+10 | 3.44912e+06 | 0.0404614 | 2.04563 | 2(Loss) | true |
| simdjson (ondemand) | 998.105 | 0.241978 | 7707.66ms | 5373214 | 80 | 1.23469e+10 | 5.13403e+06 | 0.113466 | 3.04486 | 3(Loss) | true |
| Glaze | 892.369 | 0.539003 | 8646.6ms | 5373214 | 30 | 2.87398e+10 | 5.74235e+06 | 0.0275073 | 3.40586 | 4(Loss) | true |
