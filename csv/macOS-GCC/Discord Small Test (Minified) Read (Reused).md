
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2320.41 | 0.176641 | 258.927ms | 4857 | 1280 | 15914.8 | 1996.2 | 0.533844 | 1(Win) | true |
| Glaze | 1904.07 | 0.329837 | 288.693ms | 4857 | 4890 | 314831 | 2432.68 | 0.324999 | 2(Loss) | true |
| Jsonifier (two-stage) | 1498.45 | 0.564883 | 356.819ms | 4857 | 1280 | 390285 | 3091.2 | 0.604502 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1123.23 | 0.529444 | 446.425ms | 4857 | 1280 | 610161 | 4123.8 | 0.521646 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1108.35 | 1.60258 | 472.799ms | 4857 | 40 | 179426 | 4179.2 | 0.358607 | 4(Tie) | true |
