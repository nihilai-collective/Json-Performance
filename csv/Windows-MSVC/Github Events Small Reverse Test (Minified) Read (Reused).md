
----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.231 | 0.24711 | 237.62ms | 1691 | 80 | 2221.52 | 2132.5 | 0.235018 | 3.98138 | 1(Win) | true |
| simdjson (ondemand) | 560.701 | 0.167074 | 314.431ms | 1691 | 4890 | 112915 | 2876.16 | 0.139512 | 5.38586 | 2(Loss) | true |
