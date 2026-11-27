
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1551.97 | 0.32893 | 496.313ms | 8051 | 4890 | 1.29495e+06 | 4947.29 | 0.878668 | 1(Win) | true |
| Jsonifier (two-stage) | 1428.63 | 0.535047 | 567.756ms | 8051 | 1280 | 1.05841e+06 | 5374.4 | 1.24945 | 2(Loss) | true |
| simdjson (reflection) | 1097.75 | 0.303735 | 696.251ms | 8051 | 4890 | 2.20695e+06 | 6994.35 | 1.54766 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 978.742 | 0.688307 | 807.728ms | 8051 | 320 | 932992 | 7844.8 | 3.44624 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 974.747 | 0.304155 | 788.906ms | 8051 | 4890 | 2.80683e+06 | 7876.95 | 2.32991 | 4(Tie) | true |
