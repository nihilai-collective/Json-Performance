
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1207.03 | 0.301761 | 388.989ms | 4857 | 80 | 10727.8 | 3837.5 | 0.065189 | 2.50386 | 1(Win) | true |
| Jsonifier (two-stage) | 964.543 | 0.0919613 | 482.909ms | 4857 | 4890 | 95370.2 | 4802.27 | 0.0472904 | 3.13668 | 2(Loss) | true |
| Glaze | 941.744 | 0.135701 | 497.07ms | 4857 | 4890 | 217844 | 4918.53 | 0.350115 | 3.21199 | 3(Loss) | true |
| simdjson (ondemand) | 724.643 | 0.0764838 | 642.999ms | 4857 | 2560 | 61188.2 | 6392.11 | 0.174471 | 4.17856 | 4(Loss) | true |
