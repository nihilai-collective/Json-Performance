
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1009.6 | 0.184492 | 5228.67ms | 108313 | 2560 | 9.12139e+07 | 102314 | 0.00576539 | 3.0096 | 1(Win) | true |
| simdjson (ondemand) | 881.641 | 0.174693 | 5976.29ms | 108313 | 1280 | 5.36213e+07 | 117163 | 0.0296818 | 3.44642 | 2(Loss) | true |
