
----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 496.677 | 0.116785 | 993.668ms | 4669 | 40 | 4384.62 | 8965 | 0.0557414 | 6.10493 | 1(Win) | true |
| simdjson (ondemand) | 194.611 | 0.420382 | 2354.02ms | 4669 | 80 | 740101 | 22880 | 0.16363 | 15.6046 | 2(Loss) | true |
