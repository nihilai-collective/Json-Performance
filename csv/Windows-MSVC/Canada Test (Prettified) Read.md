
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 922.44 | 1.10356 | 8158.95ms | 5212421 | 30 | 1.061e+11 | 5.38892e+06 | 0.227234 | 3.29463 | 1(Win) | true |
| simdjson (ondemand) | 852.792 | 0.804235 | 8675.41ms | 5212421 | 40 | 8.79062e+10 | 5.82904e+06 | 0.565969 | 3.5637 | 2(Loss) | true |
