
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 797.798 | 0.552166 | 157.242ms | 1213 | 40 | 2564.1 | 1450 | 0.230415 | 3.04042 | 1(Win) | true |
| Glaze | 349.753 | 0.127517 | 355.875ms | 1213 | 40 | 711.538 | 3307.5 | 0.276382 | 6.98918 | 2(Loss) | true |
| simdjson (ondemand) | 261.13 | 0.165643 | 470.137ms | 1213 | 40 | 2153.85 | 4430 | 0.0753012 | 9.40695 | 3(Loss) | true |
