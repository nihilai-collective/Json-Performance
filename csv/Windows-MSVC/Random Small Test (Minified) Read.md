
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 859.465 | 0.176067 | 580.694ms | 5094 | 4890 | 484315 | 5652.37 | 0.116844 | 2.85747 | 1(Win) | true |
| Jsonifier (two-stage) | 772.34 | 0.220266 | 650.91ms | 5094 | 30 | 5758.62 | 6290 | 0.0530223 | 3.18881 | 2(Loss) | true |
| Glaze | 626.437 | 0.150246 | 810.105ms | 5094 | 80 | 10860.8 | 7755 | 0.258565 | 3.92818 | 3(Loss) | true |
| simdjson (ondemand) | 337.91 | 0.165691 | 937.192ms | 5094 | 30 | 17023 | 14376.7 | 0.254394 | 7.30709 | 4(Loss) | true |
